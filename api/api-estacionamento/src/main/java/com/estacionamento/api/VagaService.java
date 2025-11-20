package com.estacionamento.api;

import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class VagaService {

    private final VagaRepository vagaRepository;

    public VagaService(VagaRepository vagaRepository) {
        this.vagaRepository = vagaRepository;
    }

    public List<Vaga> listarTodas() {
        return vagaRepository.findAll();
    }

    public Vaga buscarPorId(Long id) {
        return vagaRepository.findById(id).orElse(null);
    }

    public Vaga salvar(Vaga vaga) {
        return vagaRepository.save(vaga);
    }

    public Vaga ocupar(Long id) {
        Vaga vaga = buscarPorId(id);
        if (vaga != null) {
            vaga.setStatus("OCUPADA");
            vagaRepository.save(vaga);
        }
        return vaga;
    }

    public Vaga liberar(Long id) {
        Vaga vaga = buscarPorId(id);
        if (vaga != null) {
            vaga.setStatus("LIVRE");
            vagaRepository.save(vaga);
        }
        return vaga;
    }
}
